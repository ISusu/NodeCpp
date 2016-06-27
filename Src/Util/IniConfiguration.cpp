/******************************************************************************
 * Copyright (C) 671643387@qq.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *****************************************************************************/

#include "NodeCpp/Util/IniConfiguration.h"
#include <fstream>
#include <sstream>
#include "NodeCpp/String.h"

#define MAX_LINE_SIZE   0x10000

namespace NodeCpp
{
    namespace Util
    {
        IniConfiguration::IniConfiguration(void)
            : conf_()
            , secName_()
        {
            conf_.Key = "INI";
        }

        IniConfiguration::~IniConfiguration(void)
        {

        }

        bool IniConfiguration::open(const std::string& _file)
        {
            do 
            {
                std::ifstream _ifs(_file);
                if (!_ifs.is_open()) {
                    errorString_ = "No such file";
                    break;
                }

                int _lineIdx = 1;
                char _line[MAX_LINE_SIZE];
                while (!_ifs.eof())
                {
                    _ifs.getline(_line, MAX_LINE_SIZE);
                    if (!_parseLine(std::string(_line))) {
                        std::stringstream _ss;
                        _ss << "error on line " << _lineIdx;
                        errorString_ = _ss.str();
                        return false;
                    }
                    ++_lineIdx;
                }
                return true;
            } while (false);

            return false;
        }

        const Configuration::Any* IniConfiguration::get(const std::string& _key) const
        {
            return conf_.get(_key);
        }

        bool IniConfiguration::_parseLine(std::string& _line)
        {
            _line.erase(0, _line.find_first_not_of(" "));
            if (_line.empty() || _line[0] == ';') {
                return true;
            }

            if (_line.find_last_of(";") != std::string::npos) {
                _line.erase(_line.find_last_of(";") - 1);
            }
            if (_line.find_last_not_of(" ") != std::string::npos) {
                _line.erase(_line.find_last_not_of(" ") + 1);
            }

            std::string::size_type _pos;
            if (_line[0] == '[') {
                _pos = _line.rfind(']');
                if (_pos == std::string::npos) {
                    return false;
                }

                secName_.clear();
                secName_.append(_line, 1, _pos - 1);
                trimString(secName_, " ");

                Configuration::Any _section;
                _section.Key = secName_;
                conf_.Map[secName_] = _section;
                return true;
            }

            _pos = _line.find('=');
            if (_pos != std::string::npos) {
                Configuration::Any _kv;
                _kv.Key.append(_line, 0, _pos);
                _kv.Value.append(_line, _pos + 1, _line.length());
                trimString(_kv.Key, " ");
                trimString(_kv.Value, " ");

                if (secName_.empty()) {
                    secName_ = "__default";
                    Configuration::Any _section;
                    _section.Key = secName_;
                    _section.Map[_kv.Key] = _kv;
                    conf_.Map[secName_] = _section;
                }
                else {
                    conf_.Map[secName_].Map[_kv.Key] = _kv;
                }
            }
            return true;
        }
    }
}