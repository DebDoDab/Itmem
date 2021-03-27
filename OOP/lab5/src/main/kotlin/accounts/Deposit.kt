package accounts

import clients.Client

class Deposit(client: Client, val depositFunction: DepositFunction, var term: Int): Account(client) {

    override fun dailyBonus() {
        if (term > 0) {
            term--
        }
        storedBonus += depositFunction.dailyBonus(balance)
    }

    override fun dailyCommission() {}

    override fun checkTransactionPossibility(amountOfMoney: Float): Boolean {
        if (term > 0) {
            return false
        }
        return super.checkTransactionPossibility(amountOfMoney)
    }
}