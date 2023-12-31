#include "pch.h"
#include "JsonSerializer.h"
#include <FileHandler/FileHandler.h>
#include <stringbuffer.h>
#include <writer.h>

/// <summary>
/// Sets the currently active source.
/// </summary>
/// <param name="filePath">Path to the currently active file.</param>
/// <returns>True if successfull, false if failed</returns>
bool JsonSerializer::SetSource(const std::string& filePath)
{
    std::string data;
    FileHandler::ReadFile(filePath.c_str(), data);
    m_Document.Parse(data.c_str());
    return true;
}

/// <summary>
/// Returns the string attribute with the given name.
/// </summary>
/// <param name="attributeName">Name of the attribute.</param>
/// <param name="valueOut">Value of the attrribute.</param>
/// <returns>True if successfull, false if failed</returns>
bool JsonSerializer::GetStringAttribute(const std::string& attributeName, std::string& valueOut)
{
    if (!m_Document.HasMember(attributeName.c_str()))
        LOGANDRETURN("Document does not contain an attribute with the name {0}", attributeName);

    rapidjson::Value& value = m_Document[attributeName.c_str()];
    if (!value.IsString())
        LOGANDRETURN("Attribute '{0}' is not a string attribute.", attributeName);

    valueOut = value.GetString();

    return true;
}

/// <summary>
/// Returns the int attribute with the given name.
/// </summary>
/// <param name="attributeName">Name of the attribute.</param>
/// <param name="valueOut">Value of the attrribute.</param>
/// <returns>True if successfull, false if failed</returns>
bool JsonSerializer::GetIntAttribute(const std::string& attributeName, int& valueOut)
{
    if (!m_Document.HasMember(attributeName.c_str()))
        LOGANDRETURN("Document does not contain an attribute with the name {0}", attributeName);

    rapidjson::Value& value = m_Document[attributeName.c_str()];
    if (!value.IsInt())
        LOGANDRETURN("Attribute '{0}' is not a int attribute.", attributeName);

    valueOut = value.GetInt();
    return true;
}

/// <summary>
/// Returns the vector<string> attribute with the given name.
/// </summary>
/// <param name="attributeName">Name of the attribute.</param>
/// <param name="valueOut">Value of the attrribute.</param>
/// <returns>True if successfull, false if failed</returns>
bool JsonSerializer::GetStringVectorAttribute(const std::string& attributeName, std::vector<std::string>& valueOut)
{
    if (!m_Document.HasMember(attributeName.c_str()))
        LOGANDRETURN("Document does not contain an attribute with the name {0}", attributeName);

    rapidjson::Value& value = m_Document[attributeName.c_str()];
    if (!value.IsArray())
        LOGANDRETURN("Attribute '{0}' is not a array attribute.", attributeName);

    if(!value.GetArray()[0].IsString())
        LOGANDRETURN("Attribute '{0}' is not a string array attribute.", attributeName);

    std::vector<std::string> strings;
    for (const auto& item : value.GetArray())
        strings.push_back(item.GetString());
    valueOut = strings;

    return true;
}

/// <summary>
/// Returns the map<string, string> attribute with the given name.
/// </summary>
/// <param name="attributeName">Name of the attribute.</param>
/// <param name="valueOut">Value of the attrribute.</param>
/// <returns>True if successfull, false if failed</returns>
bool JsonSerializer::GetStringStringMapAttribute(const std::string& attributeName, std::map<std::string, std::string>& valueOut)
{
    if (!m_Document.HasMember(attributeName.c_str())) 
        LOGANDRETURN("Document does not contain an attribute with the name {0}", attributeName); 

    rapidjson::Value& value = m_Document[attributeName.c_str()]; 
    if (!value.IsArray()) 
        LOGANDRETURN("Attribute '{0}' is not a array attribute.", attributeName);

    rapidjson::GenericArray array = value.GetArray();

    if(!array[0].IsObject())
        LOGANDRETURN("Attribute '{0}' is not a map attribute.", attributeName);
    
    for (const auto& item : array) {
        for (auto it = item.MemberBegin(); it != item.MemberEnd(); ++it) {
            const std::string key = it->name.GetString();
            const std::string value = it->value.GetString();
            valueOut[key] = value;
        }
    }

    return true;
}

/// <summary>
/// Returns the preferences data.
/// </summary>
/// <param name="valueOut">Value of the attrribute.</param>
/// <returns>True if successfull, false if failed</returns>
bool JsonSerializer::GetPreferences(std::vector<Preferences::Preference>& valueOut)
{
    if (!m_Document.IsArray())
        LOGANDRETURN("Document is not an array.");

    for (const auto& prefObject : m_Document.GetArray()) { 
        if (!prefObject.IsObject())
            LOGANDRETURN("Array does not contain an object.");
                
        Preferences::Preference preference;

        // Question
        if (!prefObject.HasMember("question"))
            LOGANDRETURN("Attribute 'question' does not exist.");
        if (!prefObject["question"].IsString())
            LOGANDRETURN("Attribute 'question' is not a string.");

        preference.Question = prefObject["question"].GetString();

        // Answer
        if (!prefObject.HasMember("answer"))
            LOGANDRETURN("Attribute 'answer' does not exist.");
        if (!prefObject["answer"].IsString())
            LOGANDRETURN("Attribute 'answer' is not a string.");

        preference.Answer = prefObject["answer"].GetString();

        // Options
        if (!prefObject.HasMember("options"))
            LOGANDRETURN("Attribute 'options' does not exist.");
        if (!prefObject["options"].IsArray())
            LOGANDRETURN("Attribute 'options' is not an array.");

        const auto& choicesArray = prefObject["options"];
        for (const auto& choiceValue : choicesArray.GetArray()) {
            if (choiceValue.IsString()) {
                preference.Options.push_back(choiceValue.GetString());
            }
        }

        valueOut.push_back(preference);
    }

    return true;
}

/// <summary>
/// Sets the preferences data.
/// </summary>
/// <param name="value">List of preferences, containing data.</param>
/// <returns>True if successfull, false if failed</returns>
bool JsonSerializer::SetPreferences(const std::string& filePath, std::vector<Preferences::Preference>& value)
{
    if (!m_Document.IsArray()) 
        LOGANDRETURN("Document is not an array."); 

    unsigned int index = 0;
    for (rapidjson::Value& prefObject : m_Document.GetArray()) {
        if (!prefObject.IsObject())
            LOGANDRETURN("Array does not contain an object.");

        // Answer
        if (!prefObject.HasMember("answer"))
            LOGANDRETURN("Attribute 'answer' does not exist.");
        if (!prefObject["answer"].IsString())
            LOGANDRETURN("Attribute 'answer' is not a string.");
        prefObject["answer"].SetString(value[index].Answer.c_str(), value[index].Answer.size());

        index++;
    }

    rapidjson::StringBuffer buffer;
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    m_Document.Accept(writer);
    FileHandler::WriteFile(filePath, buffer.GetString());

    return true;
}
