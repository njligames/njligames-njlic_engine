//
//  easylogger.cpp
//  EasyLogger-Test
//
//  Created by James Folk on 4/19/18.
//

#include "easylogger.h"

namespace easylogger
{
    namespace _private
    {

        _private::LogSink::~LogSink()
        {
            _logger->WriteLog(Level(), _logger, _file, _line, _func,
                              _os.str().c_str());
        }
    } // namespace _private

} // namespace easylogger
