#include "stdafx.h"
#include "callback.hpp"

namespace Callback
{
	namespace Read
	{
		/*size_t file(char * ptr, size_t item_size, size_t item_count, void * file_stream)
		{
			auto file = (FILE *)file_stream;
			size_t read_bytes = fread(ptr, item_size, item_count, file);
			return read_bytes;
		}*/

		size_t file(char * ptr, size_t item_size, size_t item_count, void * file_stream)
		{
			auto in_stream = (std::ifstream *)file_stream;
			size_t write_bytes = item_size * item_count;
			in_stream->read(ptr, write_bytes);
			return write_bytes;
		}

		size_t buffer(char * ptr, size_t item_size, size_t item_count, void * buffer)
		{
			auto data = (Data*)buffer;
			auto size = item_size * item_count;
			auto copied_bytes = std::min(size, data->size - data->position);
			memcpy(ptr, data->buffer, copied_bytes);
			data->position += copied_bytes;
			return copied_bytes;
		}
	}

	namespace Write
	{
		size_t file(char * ptr, size_t item_size, size_t item_count, void * file_stream)
		{
			auto out_stream = (std::ofstream *)file_stream;
			size_t write_bytes = item_size * item_count;
			out_stream->write(ptr, write_bytes);
			return write_bytes;
		}

		size_t buffer(char * ptr, size_t item_size, size_t item_count, void * buffer)
		{
			auto data = (Data*)buffer;
			auto size = item_size * item_count;
			auto copied_bytes = std::min(size, data->size - data->position);
			memcpy(data->buffer, data->buffer, copied_bytes);
			data->position += copied_bytes;
			return copied_bytes;
		}
	}

	namespace Append
	{
		size_t buffer(char * ptr, size_t item_size, size_t item_count, void * buffer)
		{
			auto data = (Data*)buffer;
			auto append_size = item_size * item_count;
			auto new_buffer_size = data->size + append_size;
			auto new_buffer = new char[new_buffer_size];
			if (data->size != 0) memcpy(new_buffer, data->buffer, data->size);
			memcpy(new_buffer + data->size, ptr, append_size);
			delete[] data->buffer;
			data->buffer = new_buffer;
			data->size = new_buffer_size;
			return append_size;
		}
	}
}