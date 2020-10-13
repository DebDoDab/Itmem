import parser.*
import java.io.File
import java.io.FileNotFoundException


fun main(args: Array<String>) {
    if (args.size != 4) {
        System.err.println("Wrong arguments\nType filename, section, property, type(Int|Double|String)")
        return
    }
    val filename = args[0]
    val section = args[1]
    val property = args[2]
    val type = args[3]

    val parser = INIParser()
    val data: Data
    try {
        data = parser.parse(File(filename))
    } catch (e: InvalidFileFormatException) {
        System.err.println(e.message)
        return
    } catch (e: FatalErrorException) {
        System.err.println(e.message)
        return
    } catch (e: FileNotFoundException) {
        System.err.println("File with that name does not exist (or we don't have access to it)")
        return
    }

    try {
        when (type.toLowerCase().replace(Regex("\\s"), "")) {
            "int" -> println(data.tryGet<Int>(section, property))
            "string" -> println(data.tryGet<String>(section, property))
            "double" -> println(data.tryGet<Double>(section, property))
            else -> {
                System.err.println("Wrong type\nSupported types are Int, Double, String")
            }
        }
    } catch (e: SectionNotFoundException) {
        System.err.println(e.message)
        return
    } catch (e: PropertyNotFoundException) {
        System.err.println(e.message)
        return
    } catch (e: InvalidValueTypeException) {
        System.err.println(e.message)
    }
}