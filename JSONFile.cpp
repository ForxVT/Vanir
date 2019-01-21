#include <Vanir/JSONFile.h>
#include <Vanir/FileUtils.h>
#include <Vanir/Logger.h>
#include <iomanip>
#include <fstream>

namespace Vanir
{
    void JSONFile::Load(const std::string &filepath)
    {
        m_filepath = filepath;

        if (!Vanir::FileUtils::FileExist(m_filepath))
            Vanir::FileUtils::AddFile(m_filepath, "{}\n");

        std::ifstream fileStream(m_filepath, std::ifstream::in);

        fileStream >> Content;

        fileStream.close();
    }

    void JSONFile::Save()
    {
        if (!m_filepath.empty())
        {
            std::ofstream fileStream(m_filepath, std::ofstream::trunc);

            fileStream << std::setw(4) << Content << std::endl;
            fileStream.close();

            Content.clear();
        }
        else
        {
            VANIR_LOG_WARNING("You cannot save a JSON file without opening one before.");
        }
    }

    const std::string &JSONFile::GetFilepath() const
    {
        return m_filepath;
    }


} /* Namespace Vanir. */