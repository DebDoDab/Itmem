package parser

class Data {
    var data = mutableMapOf<String, Section>()

    fun addSection(name: String) {
        data[name] = Section(name)
    }

    fun addProperty(section: String, property: String, value: String) {
        if (!data.containsKey(section)) {
            throw FatalErrorException("Something went wrong :|")
        }
        data[section]!!.addProperty(property, value)
    }

    fun tryGetInt(section: String, property: String): Int {
        if (!data.containsKey(section)) {
            throw SectionNotFoundException("Section with name $section doesn't exists")
        }
        try {
            return data[section]!!.tryGetInt(property)
        } catch (e: PropertyNotFoundException) {
            throw PropertyNotFoundException("Property $property does not exist in section $section")
        }
    }

    fun tryGetString(section: String, property: String): String {
        if (!data.containsKey(section)) {
            throw SectionNotFoundException("Section with name $section doesn't exists")
        }
        try {
            return data[section]!!.tryGetString(property)
        } catch (e: PropertyNotFoundException) {
            throw PropertyNotFoundException("Property $property does not exist in section $section")
        }
    }

    fun tryGetDouble(section: String, property: String): Double {
        if (!data.containsKey(section)) {
            throw SectionNotFoundException("Section with name $section doesn't exists")
        }
        try {
            return data[section]!!.tryGetDouble(property)
        } catch (e: PropertyNotFoundException) {
            throw PropertyNotFoundException("Property $property does not exist in section $section")
        }
    }

    inline fun <reified T> tryGet(section: String, property: String): T {
        if (!data.containsKey(section)) {
            throw SectionNotFoundException("Section with name $section doesn't exists")
        }
        try {
            return data[section]!!.tryGet(property)
        } catch (e: PropertyNotFoundException) {
            throw PropertyNotFoundException("Property $property does not exist in section $section")
        }
    }
}