#include "pch.h"
#include "XmlSerializer.h"
#include <FileHandler/FileHandler.h>

bool XmlSerializer::SetSource(const std::string& filePath)
{
    std::string data;
    FileHandler::ReadFile(filePath.c_str(), data);
    m_Document.Parse(data.c_str());
    return true;
}

bool XmlSerializer::GetStringAttribute(const std::string& attributeName, std::string& valueOut)
{
    tinyxml2::XMLElement* root = m_Document.RootElement();
    tinyxml2::XMLElement* element = root->FirstChildElement(attributeName.c_str());

    if(!element)
        LOGANDRETURN("Document does not contain an attribute with the name {0}", attributeName);

    valueOut = element->GetText();
    return true;
}

bool XmlSerializer::GetIntAttribute(const std::string& attributeName, int& valueOut)
{
    int result; 
    int output;

    tinyxml2::XMLElement* root = m_Document.RootElement(); 
    result = root->QueryIntAttribute(attributeName.c_str(), &output); 
    if (!result) 
        LOGANDRETURN("Document does not contain an attribute with the name {0}", attributeName); 

    valueOut = output; 
    return true;
}

bool XmlSerializer::GetStringVectorAttribute(const std::string& attributeName, std::vector<std::string>& valueOut)
{
    tinyxml2::XMLElement* root = m_Document.RootElement();
    tinyxml2::XMLElement* element = root->FirstChildElement(attributeName.c_str()); 

    if (!element) 
        LOGANDRETURN("Document does not contain an attribute with the name {0}", attributeName);

    for (tinyxml2::XMLElement* languageFileElement = element->FirstChildElement("LanguageFile");
        languageFileElement;
        languageFileElement = languageFileElement->NextSiblingElement("LanguageFile")) {
        const char* languageFilePath = languageFileElement->GetText();
        if (languageFilePath) {
            valueOut.push_back(languageFilePath);
        }
    }

    return true;
}

bool XmlSerializer::GetStringStringMapAttribute(const std::string& attributeName, std::map<std::string, std::string>& valueOut)
{
    tinyxml2::XMLElement* root = m_Document.RootElement();
    tinyxml2::XMLElement* languageKeyValuesElement = root->FirstChildElement("LanguageKeyValues");

    // Iterate over KeyValue elements
    for (tinyxml2::XMLElement* keyValueElement = languageKeyValuesElement->FirstChildElement("KeyValue");
        keyValueElement;
        keyValueElement = keyValueElement->NextSiblingElement("KeyValue")) {

        // Extract the Key and Value elements
        tinyxml2::XMLElement* keyElement = keyValueElement->FirstChildElement("Key");
        tinyxml2::XMLElement* valueElement = keyValueElement->FirstChildElement("Value");

        if (keyElement && valueElement) {
            const char* key = keyElement->GetText();
            const char* value = valueElement->GetText();

            if (key && value) {
                // Add the key-value pair to the map
                valueOut[key] = value;
            }
        }
    }

    return true;
}

bool XmlSerializer::GetPreferences(std::vector<Preferences::Preference>& valueOut)
{
    tinyxml2::XMLElement* root = m_Document.RootElement();
    for (tinyxml2::XMLElement* preferenceElement = root->FirstChildElement("Preference"); preferenceElement; preferenceElement = preferenceElement->NextSiblingElement("Preference")) {
        Preferences::Preference preference;

        // Parse 'Question' and 'Answer' elements
        tinyxml2::XMLElement* questionElement = preferenceElement->FirstChildElement("question");
        tinyxml2::XMLElement* answerElement = preferenceElement->FirstChildElement("answer");

        if(!questionElement)
            LOGANDRETURN("Document does not contain an attribute with the name 'Question'.");
        preference.Question = questionElement->GetText(); 

        if (!answerElement)
            LOGANDRETURN("Document does not contain an attribute with the name 'Answer'.");
        preference.Answer = answerElement->GetText(); 

        tinyxml2::XMLElement* optionsElement = preferenceElement->FirstChildElement("options");
        if (optionsElement) {
            const char* optionsText = optionsElement->GetText();
            const char* delimiter = ",";
            char* token = std::strtok(const_cast<char*>(optionsText), delimiter);
            while (token != nullptr) {
                preference.Options.push_back(token);
                token = std::strtok(nullptr, delimiter);
            }
        }
        valueOut.push_back(preference);
    }

    return true;
}

bool XmlSerializer::SetPreferences(const std::string& filePath, std::vector<Preferences::Preference>& value)
{
    tinyxml2::XMLElement* root = m_Document.RootElement();
    unsigned int index = 0;
    for (tinyxml2::XMLElement* preferenceElement = root->FirstChildElement("Preference"); preferenceElement; preferenceElement = preferenceElement->NextSiblingElement("Preference")) {

        tinyxml2::XMLElement* answerElement = preferenceElement->FirstChildElement("answer");

        if (!answerElement) 
            LOGANDRETURN("Document does not contain an attribute with the name 'Answer'."); 
        answerElement->SetText(value[index].Answer.c_str());

        index++;
    }

    m_Document.SaveFile(filePath.c_str());

    return true;
}
