#pragma once

struct Data
{
	char * buffer;
	unsigned long long int position;
	unsigned long long int size;
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