#include <pugixml.hpp>

namespace pugi
{
	class PUGIXML_CLASS xml_string_writer: public xml_writer
	{
	public:
		std::string result;

		virtual void write(const void* data, size_t size)
		{
			result += std::string(static_cast<const char*>(data), size);
		}
	};

	std::string node_to_string(pugi::xml_node node)
	{
		xml_string_writer writer;
		node.print(writer);

		return writer.result;
	}
}