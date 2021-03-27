package accounts

class DepositFunction(private val percentage: MutableList<Pair<Float, Float>>) {
    fun dailyBonus(balance: Float): Float {
        var bonus: Float = 0F
        for (balanceLimit in percentage) {
            if (balance >= balanceLimit.first) {
                bonus = balanceLimit.second
            } else {
                break
            }
        }
        return bonus
    }
}