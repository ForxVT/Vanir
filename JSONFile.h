#ifdef VANIR_USE_JSON

#ifndef VANIR_SETTINGS_H
#define VANIR_SETTINGS_H

#include <nlohmann/json.hpp>

namespace Vanir
{
    class JSONFile
    {
    public:
        void Load(const std::string& filepath);
        void Save();
        const std::string& GetFilepath() const;

        nlohmann::json Content;

    private:
        std::string m_filepath;
    };

} /* Namespace Vanir. */

#endif /* VANIR_SETTINGS_H. */

#endif