#include "uiProjectBuilder.h"

#include "uiScene.h"
#include "uiFileSystem.h"
#include "uiSceneManager.h"
#include "uiResourceManager.h"
#include "uiJSON.h"
#include "uiUtilities.h"
#include "uiVector2.h"

// TODO: Make Windows specific checks
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


#pragma pack(push, 2) 
struct ICONDIR {
  WORD idReserved;   
  WORD idType;      
  WORD idCount;    
};

struct ICONDIRENTRY {
  BYTE bWidth;        
  BYTE bHeight;       
  BYTE bColorCount;   
  BYTE bReserved;     
  WORD wPlanes;       
  WORD wBitCount;     
  DWORD dwBytesInRes; 
  DWORD dwImageOffset; 
};

struct GRPICONDIRENTRY {
  BYTE bWidth;
  BYTE bHeight;
  BYTE bColorCount;
  BYTE bReserved;
  WORD wPlanes;
  WORD wBitCount;
  DWORD dwBytesInRes;
  WORD nID; 
};
#pragma pack(pop)

void ProjectBuilder::Initialize()
{
  

}

void ProjectBuilder::BuildProject()
{

  // App Settings

  // Copy the folder of the executable
  Path editorPath = FileSystem::ExePath().parent_path();
  Path newDirPath = Path(Utils::Format("%s/%s", m_settings.m_projectDir.c_str(), "Build"));

  if (!FileSystem::Exists(newDirPath))
  {
    FileSystem::CreateDirectories(newDirPath);
  }

  if (!FileSystem::IsEmpty(newDirPath))
  {
    FileSystem::EraseAll(newDirPath);
  }

  FileSystem::Copy(editorPath, newDirPath);

  Path newExePath(Utils::Format("%s/%s.exe", newDirPath.string().c_str(), m_settings.m_projectName.c_str()));
  Path oldExePath(Utils::Format("%s/%s.exe", newDirPath.string().c_str(), "UIDesignd"));
  String newExeString = newExePath.string().c_str();
  FileSystem::Rename(oldExePath, newExePath);
  //////////////////////////////////////////////////////////////////////////
  JSONDocument gameDocument;
  gameDocument.SetObject();
  JSONDocument::AllocatorType& allocator = gameDocument.GetAllocator();
  JSONValue settingsData(rapidjson::kObjectType);

  settingsData.AddMember("name", m_settings.m_projectName, allocator);

  gameDocument.AddMember("settings", settingsData, allocator);

  JSONValue sceneData(rapidjson::kArrayType);

  for (int i = 0; i < m_settings.m_cookableScenes.size(); ++i)
  {
    if (m_settings.m_cookableScenes[i] != nullptr)
    {
      JSONDocument scene = m_settings.m_cookableScenes[i]->Serialize();
      sceneData.PushBack(std::move(scene), allocator);
    }
  }

  gameDocument.AddMember("scenes", sceneData, allocator);


  // Resources being used
  JSONDocument resourcesDocument = ResourceManager::Instance().Serialize();
  gameDocument.AddMember("resources", JSONValue(resourcesDocument, allocator), allocator);

  OFStream ofs(Utils::Format("%s/%s", newDirPath.string().c_str(), "game.package").c_str());
  JSONOStream os(ofs);
  JSONWriter<JSONOStream> writer(os);
  gameDocument.Accept(writer);

  //////////////////////////////////////////////////////////////////////////
  // ICON STUFF

  // TODO: Clean this mess

  m_settings.m_projectIcon = ResourceManager::Instance().GetResource<Texture>(m_projectIconStr).get();

  ULONG_PTR token;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  Gdiplus::GdiplusStartup(&token, &gdiplusStartupInput, NULL);

  const sf::Image& image = m_settings.m_projectIcon->copyToImage();
  const unsigned char* pixels = image.getPixelsPtr();
  int width = image.getSize().x;
  int height = image.getSize().y;

  // Create an empty GDI+ Bitmap
  Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(width, height, PixelFormat32bppARGB);

  // Lock the bitmap to write pixel data
  Gdiplus::BitmapData bitmapData;
  Gdiplus::Rect rect(0, 0, width, height);
  bitmap->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &bitmapData);

  // Copy pixel data from SFML to GDI+ Bitmap
  unsigned char* bitmapPixels = static_cast<unsigned char*>(bitmapData.Scan0);
  memcpy(bitmapPixels, pixels, width * height * 4);  // 4 bytes per pixel (RGBA)

  bitmap->UnlockBits(&bitmapData);

  // Save temporarily the icon file

  OFStream icoFile(Utils::Format("%s/%s", newDirPath.string().c_str(), "icon.ico"), std::ios::binary);
  if (!icoFile) {
    return;
  }

  // ICO Header (6 bytes)
  uint16_t reserved = 0;     // Reserved, must be 0
  uint16_t type = 1;          // 1 for icons
  uint16_t count = 1;         // Number of images in the icon

  icoFile.write(reinterpret_cast<const char*>(&reserved), 2);
  icoFile.write(reinterpret_cast<const char*>(&type), 2);
  icoFile.write(reinterpret_cast<const char*>(&count), 2);

  // ICO Directory Entry (16 bytes)
  uint8_t iconWidth = static_cast<uint8_t>(width);
  uint8_t iconHeight = static_cast<uint8_t>(height);
  uint8_t colorCount = 0;     // 0 if >=8bpp
  uint8_t reservedByte = 0;   // Reserved, must be 0
  uint16_t planes = 1;        // Color planes
  uint16_t bitCount = 32;     // Bits per pixel
  uint32_t sizeInBytes = width * height * 4 + 40;  // Bitmap + InfoHeader size
  uint32_t offset = 22;       // Offset of the BMP data (header size + directory entry size)

  icoFile.put(iconWidth);
  icoFile.put(iconHeight);
  icoFile.put(colorCount);
  icoFile.put(reservedByte);
  icoFile.write(reinterpret_cast<const char*>(&planes), 2);
  icoFile.write(reinterpret_cast<const char*>(&bitCount), 2);
  icoFile.write(reinterpret_cast<const char*>(&sizeInBytes), 4);
  icoFile.write(reinterpret_cast<const char*>(&offset), 4);

  // Bitmap Info Header (40 bytes)
  BITMAPINFOHEADER bmpInfoHeader = {};
  bmpInfoHeader.biSize = 40;
  bmpInfoHeader.biWidth = width;
  bmpInfoHeader.biHeight = height * 2;  // Icon images are stored "upside-down"
  bmpInfoHeader.biPlanes = 1;
  bmpInfoHeader.biBitCount = 32;
  bmpInfoHeader.biCompression = BI_RGB;

  icoFile.write(reinterpret_cast<const char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

  // Bitmap Pixel Data (BGRA)
  for (int y = height - 1; y >= 0; --y) {  // Bottom-up
    for (UINT x = 0; x < width; ++x) {
      Gdiplus::Color color;
      bitmap->GetPixel(x, y, &color);

      uint8_t b = color.GetBlue();
      uint8_t g = color.GetGreen();
      uint8_t r = color.GetRed();
      uint8_t a = color.GetAlpha();

      icoFile.put(b);
      icoFile.put(g);
      icoFile.put(r);
      icoFile.put(a);
    }
  }

  // Mask Data (all 0 for full transparency)
  for (int y = 0; y < height; ++y) {
    for (UINT x = 0; x < width; ++x) {
      icoFile.put(0);  // 0 for fully opaque mask
    }
  }

  icoFile.close();

  // TODO: Set icons dynamically, instead of saving and loading

  HANDLE hUpdate = BeginUpdateResource(newExePath.string().c_str(), FALSE);
  if (!hUpdate) {
    return;
  }

  IFStream iconFile(Utils::Format("%s/%s", newDirPath.string().c_str(), "icon.ico"), std::ios::binary | std::ios::ate);
  if (!iconFile.is_open()) {
    EndUpdateResource(hUpdate, TRUE);
    return;
  }

  StreamSize iconSize = iconFile.tellg();
  iconFile.seekg(0, std::ios::beg);

  Vector<char> iconData(iconSize);
  if (!iconFile.read(iconData.data(), iconSize)) {
    EndUpdateResource(hUpdate, TRUE);
    return;
  }

  ICONDIR* iconDir = reinterpret_cast<ICONDIR*>(iconData.data());
  ICONDIRENTRY* iconEntries = reinterpret_cast<ICONDIRENTRY*>(iconData.data() + sizeof(ICONDIR));

  for (int i = 0; i < iconDir->idCount; ++i) {
    char* iconImage = iconData.data() + iconEntries[i].dwImageOffset;

    if (!UpdateResource(hUpdate,
      RT_ICON,
      MAKEINTRESOURCE(1 + i),
      MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
      iconImage,
      iconEntries[i].dwBytesInRes)) {
      EndUpdateResource(hUpdate, TRUE);
      return;
    }
  }

  SizeT groupSize = sizeof(ICONDIR) + iconDir->idCount * sizeof(GRPICONDIRENTRY);
  Vector<char> groupIconData(groupSize);

  ICONDIR* groupIconHeader = reinterpret_cast<ICONDIR*>(groupIconData.data());
  GRPICONDIRENTRY* grpEntries = reinterpret_cast<GRPICONDIRENTRY*>(groupIconData.data() + sizeof(ICONDIR));

  groupIconHeader->idReserved = iconDir->idReserved;
  groupIconHeader->idType = iconDir->idType;
  groupIconHeader->idCount = iconDir->idCount;


  for (int i = 0; i < iconDir->idCount; ++i) {
    grpEntries[i].bWidth = iconEntries[i].bWidth;
    grpEntries[i].bHeight = iconEntries[i].bHeight;
    grpEntries[i].bColorCount = iconEntries[i].bColorCount;
    grpEntries[i].bReserved = iconEntries[i].bReserved;
    grpEntries[i].wPlanes = iconEntries[i].wPlanes;
    grpEntries[i].wBitCount = iconEntries[i].wBitCount;
    grpEntries[i].dwBytesInRes = iconEntries[i].dwBytesInRes;
    grpEntries[i].nID = 1 + i;
  }

  if (!UpdateResource(hUpdate,
    RT_GROUP_ICON,
    MAKEINTRESOURCE(1),
    MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
    groupIconData.data(),
    groupSize)) {
    EndUpdateResource(hUpdate, TRUE);
    return;
  }

  if (!EndUpdateResource(hUpdate, FALSE)) {
    return;
  }

  iconFile.close();
  Path iconPath(Utils::Format("%s/%s", newDirPath.string().c_str(), "icon.ico"));
  FileSystem::Erase(iconPath);


  //////////////////////////////////////////////////////////////////////////
  Gdiplus::GdiplusShutdown(token);

}
