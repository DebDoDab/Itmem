package parser
import parser.Data
import java.io.File

class INIParser {
    private val startOfLine = "^\\s*"
    private val endOfLine = "\\s*(;.*)?\\s*$"
    private val section = "\\[([\\w_]*)\\]"
    private val property = "([\\w_]*)\\s*=\\s*([\\w\\._/]*)"

    private val emptyLine = "$startOfLine$endOfLine"
    private val sectionLine = "$startOfLine$section$endOfLine"
    private val propertyLine = "$startOfLine$property$endOfLine"

    private fun isSectionLine(line: String): Boolean {
        return Regex(sectionLine).matches(line)
    }

    private fun isPropertyLine(line: String): Boolean {
        return Regex(propertyLine).matches(line)
    }

    private fun isEmptyLine(line: String): Boolean {
        return Regex(emptyLine).matches(line)
    }

    private fun isCorrectLine(line: String): Boolean {
        return isSectionLine(line) || isPropertyLine(line) || isEmptyLine(line)
    }

    fun isCorrectINIFile(file: File): Boolean {
        for (line in file.readLines()) {
            if (!isCorrectLine(line)) {
                return false
            }
        }
        return true
    }

    private fun getSection(line: String): String {
        val matchResult = Regex(section).find(line)!!.destructured
        return matchResult.component1()
    }

    private fun getProperty(line: String): Pair<String, String> {
        val matchResult = Regex(property).find(line)!!.destructured
        return Pair(matchResult.component1(), matchResult.component2())
    }

    fun parse(file: File): Data {
        val data = Data()
        var lastSection: String? = null
        if (!isCorrectINIFile(file)) {
            throw InvalidFileFormatException("File structure is not correct")
        }

        for (line in file.readLines()) {
            if (isSectionLine(line)) {
                val sectionName = getSection(line)
                data.addSection(sectionName)
                lastSection = sectionName
            } else if (isPropertyLine(line)) {
                if (lastSection == null) {
                    throw InvalidFileFormatException("File structure is not correct")
                }
                val (property, value) = getProperty(line)
                data.addProperty(lastSection, property, value)
            } else {
                continue
            }
        }

        return data

    }
}