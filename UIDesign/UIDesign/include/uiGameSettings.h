#pragma once

#include "uiPrerequisites.h"

#include "uiUtilities.h"

#include "uiJSON.h"

#include <SFML/Window/VideoMode.hpp>

using VideoMode = sf::VideoMode;

struct GameSettings
{
  VideoMode m_displaySize;

  String m_gameName;

  bool m_shouldUseVerticalSync;

  float m_framerate;


  void ToFile(const std::string& filename) {
    OFStream file(filename, std::ios::binary);
    if (file.is_open()) {
      // Write sf::VideoMode (which contains width, height, bitsPerPixel)
      file.write(reinterpret_cast<const char*>(&m_displaySize), sizeof(m_displaySize));

      // Write the length of the string
      SizeT nameLength = m_gameName.size();
      file.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));

      // Write the string data
      file.write(m_gameName.data(), nameLength);

      // Write the bool
      file.write(reinterpret_cast<const char*>(&m_shouldUseVerticalSync), sizeof(m_shouldUseVerticalSync));

      // Write the float
      file.write(reinterpret_cast<const char*>(&m_framerate), sizeof(m_framerate));

      file.close();
    }
    else {
      std::cerr << "Failed to open file for writing.\n";
    }
  }

  void FromFile(const std::string& filename) {
    IFStream file(filename, std::ios::binary);
    if (file.is_open()) {
      // Read sf::VideoMode
      file.read(reinterpret_cast<char*>(&m_displaySize), sizeof(m_displaySize));

      // Read the length of the string
      SizeT nameLength;
      file.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

      // Resize the string to hold the incoming data
      m_gameName.resize(nameLength);

      // Read the string data
      file.read(&m_gameName[0], nameLength);

      // Read the bool
      file.read(reinterpret_cast<char*>(&m_shouldUseVerticalSync), sizeof(m_shouldUseVerticalSync));

      // Read the float
      file.read(reinterpret_cast<char*>(&m_framerate), sizeof(m_framerate));

      file.close();
    }
    else {
      std::cerr << "Failed to open file for reading.\n";
    }
  }
};