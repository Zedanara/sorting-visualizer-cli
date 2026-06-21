#pragma once
#include <string>
#include <unordered_map>

namespace sv::core {

    enum class Language { PL, EN };

    class Localization {
    private:
        static Language s_currentLanguage;
        static const std::unordered_map<std::string, std::unordered_map<Language, std::string>> s_dict;

    public:
        static void setLanguage(Language lang);
        static Language getLanguage();
        
        // Zwraca przetłumaczony tekst na podstawie klucza
        static std::string tr(const std::string& key);
    };

}