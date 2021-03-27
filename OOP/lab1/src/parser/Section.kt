package parser
import java.lang.Exception
import java.lang.NumberFormatException

class Section(val name: String) {
    var data = mutableMapOf<String, String>()

    fun addProperty(property: String, value: String) {
        data[property] = value
    }

    inline fun <reified T> tryGet(property: String): T {
        if (T::class == Int::class) {
            return tryGetInt(property) as T
        } else if (T::class == String::class) {
            return tryGetString(property) as T
        } else if (T::class == Double::class) {
            return tryGetDouble(property) as T
        }
        throw NotSupportedValueTypeException("Your value type is not supported")
    }

    fun tryGetDouble(property: String): Double {
        if (!data.containsKey(property)) {
            throw PropertyNotFoundException("Property $property does not exist in this section")
        }
        val value = data[property]!!
        try {
            return value.toDouble()
        } catch (e: NumberFormatException) {
            throw InvalidValueTypeException("Double is not supported for $value")
        }
    }

    fun tryGetString(property: String): String {
        if (!data.containsKey(property)) {
            throw PropertyNotFoundException("Property $property does not exist in this section")
        }
        val value = data[property]!!
        try {
            return value.toString()
        } catch (e: NumberFormatException) {
            throw InvalidValueTypeException("String is not supported for $value")
        }
    }

    fun tryGetInt(property: String): Int {
        if (!data.containsKey(property)) {
            throw PropertyNotFoundException("Property $property does not exist in this section")
        }
        val value = data[property]!!
        try {
            return value.toInt()
        } catch (e: NumberFormatException) {
            throw InvalidValueTypeException("Int is not supported for $value")
        }
    }
}