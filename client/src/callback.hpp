#pragma once

struct Data
{
	char* buffer;
	size_t position;
	size_t size;
};

namespace Callback
{
	namespace Read
	{
		size_t file(char * data, size_t size, size_t count, void * file_stream);
		size_t buffer(char * data, size_t size, size_t count, void * buffer);
	}

	namespace Write
	{
		size_t file(char * data, size_t size, size_t count, void * file_stream);
		size_t buffer(char * data, size_t size, size_t count, void * buffer);
	}

	namespace Append
	{
		size_t file(char * data, size_t size, size_t count, void * file_stream);
		size_t buffer(char * data, size_t size, size_t count, void * buffer);
	}
}