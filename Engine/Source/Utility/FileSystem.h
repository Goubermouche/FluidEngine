#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#include "pch.h"

#include "Core/Application.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <commdlg.h>
#include <GLFW/glfw3native.h>

namespace fe {
	class FileDialog {
	public:
		/// <summary>
		/// Opens a new file dialog and suspends the application, after the user selects a file the application resumes and a string containing the selected file path is returned. 
		/// </summary>
		/// <param name="filter">File extension filter.</param>
		/// <returns>String containing the selected item's file path, if no item was selected an empty string is returned.</returns>
		static std::string OpenFile(const char* filter) {
			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };

			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileNameA(&ofn) == TRUE) {
				return ofn.lpstrFile;
			}

			return std::string();
		}

		/// <summary>
		/// Opens a new file dialog and suspends the application, after the user selects a file the application resumes and a string containing the selected file path is returned. 
		/// </summary>
		/// <param name="filter">File extension filter.</param>
		/// <param name="defaultExtension">Default file extension.</param>
		/// <returns></returns>
		static std::string SaveFile(const char* filter, const char* defaultExtension = NULL) {
			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };

			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
			ofn.lpstrDefExt = defaultExtension;

			if (GetSaveFileNameA(&ofn) == TRUE) {
				return ofn.lpstrFile;
			}

			return std::string();
		}
	};

	static bool FileExists(const std::string& filepath) {
		struct stat buffer;
		return (stat(filepath.c_str(), &buffer) == 0);
	}

	static std::string FilenameFromFilepath(const std::string& filepath) {
		return std::filesystem::path(filepath).stem().string();
	}
}

#endif // !FILE_SYSTEM_H_