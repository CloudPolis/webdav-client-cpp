#include <pugixml/pugixml.hpp>

namespace pugi
{
	PUGIXML_CLASS struct xml_string_writer: public xml_writer
	{
		std::string result;

		virtual void write(const void* data, size_t size)
		{
			result += std::string(static_cast<const char*>(data), size);
		}
	};

	PUGIXML_FUNCTION std::string node_to_string(pugi::xml_node node)
	{
		xml_string_writer writer;
		node.print(writer);

		return writer.result;
	}
}