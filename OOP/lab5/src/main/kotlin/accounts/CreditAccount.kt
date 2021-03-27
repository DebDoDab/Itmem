package accounts

import clients.Client

class CreditAccount(client: Client, val limit: Float, val commission: Float): Account(client) {

    override fun dailyBonus() {}

    override fun dailyCommission() {
        if (balance < 0) {
            balance -= commission
        }
    }

    override fun checkTransactionPossibility(amountOfMoney: Float): Boolean {
        if (frozen) {
            return false
        }
        return (balance + limit) >= amountOfMoney
    }
}