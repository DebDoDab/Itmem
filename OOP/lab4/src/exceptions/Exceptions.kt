package exceptions

class CannotCreateIncrementalRestorePointException(message: String): Exception(message)

class EmptyBackupException(message: String): Exception(message)