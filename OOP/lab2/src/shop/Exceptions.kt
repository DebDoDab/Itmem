package shop

import java.lang.Exception

class NotEnoughInStockException(message: String): Exception(message)

class NoPriceException(message: String): Exception(message)
