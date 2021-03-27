package accounts

import clients.Client

class DebitAccount(client: Client, val dailyBonusPercentage: Float): Account(client) {

    override fun dailyBonus() {
        storedBonus += balance * dailyBonusPercentage
    }

    override fun dailyCommission() {}

}