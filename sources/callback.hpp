/*#***************************************************************************
#                         __    __   _____       _____
#   Project              |  |  |  | |     \     /  ___|
#                        |  |__|  | |  |\  \   /  /
#                        |        | |  | )  ) (  (     
#                        |   /\   | |  |/  /   \  \___
#                         \_/  \_/  |_____/     \_____|
#
# Copyright (C) 2016, The WDC Project, <designerror@yandex.ru>, et al.
#
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution. 
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the LICENSE file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
############################################################################*/

#ifndef WEBDAV_CALLBACK_H
#define WEBDAV_CALLBACK_H
#pragma once

namespace WebDAV
{
	struct Data
	{
		char * buffer;
		unsigned long long position;
		unsigned long long size;
	};
	
	namespace Callback
	{
		namespace Read
		{
			size_t stream(char * data, size_t size, size_t count, void * stream);
			size_t buffer(char * data, size_t size, size_t count, void * buffer);
		}
	
		namespace Write
		{
			size_t stream(char * data, size_t size, size_t count, void * stream);
			size_t buffer(char * data, size_t size, size_t count, void * buffer);
		}
	
		namespace Append
		{
			size_t stream(char * data, size_t size, size_t count, void * stream);
			size_t buffer(char * data, size_t size, size_t count, void * buffer);
		}
	}
}

#endif
