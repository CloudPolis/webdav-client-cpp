#include "stdafx.h"
#include "callback.hpp"

#include <algorithm>

namespace Callback
{
	namespace Read
	{
		size_t stream(char * ptr, size_t item_size, size_t item_count, void * stream)
		{
			auto in_stream = (std::istream *)stream;
			auto read_bytes = static_cast<unsigned long long>(item_size * item_count);
			unsigned long long position = in_stream->tellg();
			in_stream->seekg(0, std::ios::end);
			auto size = static_cast<unsigned long long>(in_stream->tellg());
			in_stream->seekg(position, std::ios::beg);
			read_bytes = std::min(read_bytes, size - position);
			in_stream->read(ptr, read_bytes);
			return read_bytes;
		}

		size_t buffer(char * ptr, size_t item_size, size_t item_count, void * buffer)
		{
			auto data = (Data*)buffer;
			auto size = static_cast<unsigned long long>(item_size * item_count);
			auto copied_bytes = std::min(size, data->size - data->position);
			memcpy(ptr, data->buffer, copied_bytes);
			data->position += copied_bytes;
			return copied_bytes;
		}
	}

	namespace Write
	{
		size_t stream(char * ptr, size_t item_size, size_t item_count, void * stream)
		{
			auto out_stream = (std::ostream *)stream;
			size_t write_bytes = item_size * item_count;
			out_stream->write(ptr, write_bytes);
			return write_bytes;
		}

		size_t buffer(char * ptr, size_t item_size, size_t item_count, void * buffer)
		{
			auto data = (Data*)buffer;
			auto size = static_cast<unsigned long long>(item_size * item_count);
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

		size_t stream(char * ptr, size_t item_size, size_t item_count, void * stream)
		{
			auto out_stream = (std::ostream *)stream;
			size_t write_bytes = item_size * item_count;
			out_stream->seekp(0, std::ios::end);
			out_stream->write(ptr, write_bytes);
			return write_bytes;
		}
	}
}
