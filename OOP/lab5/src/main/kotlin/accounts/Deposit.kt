package accounts

import clients.Client

class Deposit(client: Client): Account(client) {

    override fun dailyBonus() {

    }

    override fun dailyCommission() {}
}