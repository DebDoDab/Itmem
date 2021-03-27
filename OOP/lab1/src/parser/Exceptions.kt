package parser

import java.lang.Exception

class InvalidValueTypeException(message: String): Exception(message)

class InvalidFileFormatException(message: String): Exception(message)

class PropertyNotFoundException(message: String): Exception(message)

class SectionNotFoundException(message: String): Exception(message)

class NotSupportedValueTypeException(message: String): Exception(message)

class FatalErrorException(message: String): Exception(message)
