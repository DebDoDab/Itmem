package accounts

import clients.Client
import transactions.Transaction

abstract class Account(val client: Client) {
    companion object {
        var lastUsedId = 0

        fun getNewId(): Int {
            return lastUsedId++
        }
    }

    val id: Int = getNewId()

    var frozen: Boolean = false
    var balance: Float = 0F
    var storedBonus: Float = 0F
    var bonusDay: Int = 0
    val transactions = mutableListOf<Transaction>()

    abstract fun dailyBonus()

    fun monthlyBonus() {
        balance += storedBonus
        storedBonus = 0F
    }

    abstract fun dailyCommission()

    open fun checkTransactionPossibility(amountOfMoney: Float): Boolean {
        if (frozen) {
            return false
        }
        if (client.isDoubtful() && amountOfMoney > client.bank.doubtfulLimit) {
            return false
        }
        return balance >= amountOfMoney
    }

    fun cancelTransaction(transaction: Transaction) {
        if (transaction in transactions) {
            transaction.cancel()
        }
    }

    fun addMoney(amountOfMoney: Float): Boolean {
        if (frozen) {
            return false
        }
        if (client.isDoubtful() && amountOfMoney > client.bank.doubtfulLimit) {
            return false
        }
        balance += amountOfMoney
        return true
    }

    fun substractMoney(amountOfMoney: Float): Boolean {
        if (!checkTransactionPossibility(amountOfMoney)) {
            return false
        }
        balance -= amountOfMoney
        return true
    }
}