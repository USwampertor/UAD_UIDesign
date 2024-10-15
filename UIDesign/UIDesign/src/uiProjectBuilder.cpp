#include "uiProjectBuilder.h"

#include "uiScene.h"
#include "uiFileSystem.h"
#include "uiJSON.h"
#include "uiUtilities.h"
#include "uiVector2.h"

// TODO: Make Windows specific checks
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


void ProjectBuilder::Initialize()
{
  ULONG_PTR token;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  Gdiplus::GdiplusStartup(&token, &gdiplusStartupInput, NULL);

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
  JSONDocument::AllocatorType& allocator = gameDocument.GetAllocator();
  JSONValue settingsData(rapidjson::kObjectType);

  settingsData.AddMember("name", m_settings.m_projectName, allocator);

  gameDocument.AddMember("settings", settingsData, allocator);

  JSONDocument sceneData(rapidjson::kObjectType);


  gameDocument.AddMember("scenes", sceneData, allocator);

  JSONDocument resourcesData(rapidjson::kObjectType);

  //////////////////////////////////////////////////////////////////////////
  // ICON STUFF

  return;

  const sf::Image img = m_settings.m_icon->copyToImage();
  const sf::Uint8* pixels = img.getPixelsPtr();
  Vector2u size = img.getSize();

  Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(size.x, size.y, PixelFormat32bppARGB);

  if (!bitmap) {
    // Was not able to create a bitmap
    delete bitmap;
  }
  for (int y = 0; y < size.y; ++y) {
    for (int x = 0; x < size.x; ++x) {
      sf::Uint8 r = pixels[(y * size.x + x) * 4 + 0];
      sf::Uint8 g = pixels[(y * size.x + x) * 4 + 1];
      sf::Uint8 b = pixels[(y * size.x + x) * 4 + 2];
      sf::Uint8 a = pixels[(y * size.x + x) * 4 + 3];
      Gdiplus::Color color(a, r, g, b);  // ARGB format for GDI+
      bitmap->SetPixel(x, y, color);
    }
  }

  ICONINFO iconInfo = {};
  iconInfo.fIcon = TRUE;  // TRUE means it's an icon, not a cursor

  // Create a HBITMAP from the GDI+ Bitmap for both the mask and color
  bitmap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &iconInfo.hbmColor);
  iconInfo.hbmMask = CreateBitmap(bitmap->GetWidth(), bitmap->GetHeight(), 1, 1, nullptr);

  // Create an HICON from the ICONINFO structure
  HICON hIcon = CreateIconIndirect(&iconInfo);

  // Clean up
  DeleteObject(iconInfo.hbmColor);
  DeleteObject(iconInfo.hbmMask);

  HANDLE hUpdate = BeginUpdateResource(newExePath.string().c_str(), FALSE);


  // Icon directory (group)
  struct GRPICONDIRENTRY {
    BYTE  bWidth;
    BYTE  bHeight;
    BYTE  bColorCount;
    BYTE  bReserved;
    WORD  wPlanes;
    WORD  wBitCount;
    DWORD dwBytesInRes;
    WORD  nID;
  };

  struct GRPICONDIR {
    WORD idReserved;
    WORD idType;
    WORD idCount;
    GRPICONDIRENTRY idEntries[1];  // Dynamically sized
  };

  // Dummy icon group structure (simplified for a single icon)
  GRPICONDIR grpIconDir = {};
  grpIconDir.idReserved = 0;
  grpIconDir.idType = 1;  // 1 = icon
  grpIconDir.idCount = 1;
  grpIconDir.idEntries[0].bWidth = 32;
  grpIconDir.idEntries[0].bHeight = 32;
  grpIconDir.idEntries[0].wPlanes = 1;
  grpIconDir.idEntries[0].wBitCount = 32;
  grpIconDir.idEntries[0].dwBytesInRes = 0;  // Not used in this example
  grpIconDir.idEntries[0].nID = 1;  // Resource ID

  // Update the icon group
  if (!UpdateResource(hUpdate, RT_GROUP_ICON, MAKEINTRESOURCE(1), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), &grpIconDir, sizeof(GRPICONDIR))) {
    EndUpdateResource(hUpdate, TRUE);
  }

  // Finalize the resource update
  if (!EndUpdateResource(hUpdate, FALSE)) {
  }

  //////////////////////////////////////////////////////////////////////////


}
