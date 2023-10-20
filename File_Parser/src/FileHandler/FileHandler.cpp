#include "pch.h"
#include "FileHandler.h"

#define LOGANDRETURN(...) { LOG_ERROR(__VA_ARGS__); return false; }

bool FileHandler::ReadFile(std::string& filePath, std::string& dataOut)
{
    FILE* file = nullptr;
    errno_t error = fopen_s(&file, filePath.c_str(), "rb");

    if (error)
        LOGANDRETURN("Error opening the file for reading. Error code: {0}", error);

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(fileSize + 1);

    if (!buffer)
        LOGANDRETURN("Failed to allocate memory.");

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize)
        LOGANDRETURN("Failed to read the file.");
    
    buffer[fileSize] = '\0';
    dataOut = buffer;
    free(buffer);

    return true;
}

bool FileHandler::WriteFile(std::string& filePath, const char* data)
{
    FILE* file = nullptr;
    errno_t error = fopen_s(&file, filePath.c_str(), "wb");

    if (error)
        LOGANDRETURN("Error opening the file for writing. Error code: {0}", error);

    size_t dataSize = strlen(data);
    size_t bytesWritten = fwrite(data, 1, dataSize, file);

    if (bytesWritten != dataSize)
        LOGANDRETURN("Failed to write to the file.");

    fclose(file);
    return true;
}
