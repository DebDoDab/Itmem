package transactions

import accounts.Account

class Transaction(private val source: Account, private val destination: Account, private val amountOfMoney: Float) {
    companion object {
        private var lastUsedId = 0

        private fun getNewId(): Int {
            return lastUsedId++
        }
    }

    val id: Int = getNewId()

    var status: String = "Processing" //"Processing", "Failed", "Canceled", "Passed"
        private set

    private fun checkPossibility(): Boolean {
        if (source.client.isDoubtful() && source.client.bank.doubtfulLimit < amountOfMoney ||
                destination.client.isDoubtful() && destination.client.bank.doubtfulLimit < amountOfMoney) {
            return false
        }
        if (!source.checkTransactionPossibility(amountOfMoney)) {
            return false
        }
        return true
    }

    fun proceed(): Boolean {
        if (status != "Processing") {
            return false
        }
        if (!checkPossibility()) {
            status = "Failed"
            return false
        }
        source.balance -= amountOfMoney
        destination.balance += amountOfMoney
        status = "Passed"
        return true
    }

    fun cancel(): Boolean {
        if (status != "Passed") {
            return false
        }
        source.balance += amountOfMoney
        destination.balance -= amountOfMoney
        status = "Canceled"
        return true
    }
}