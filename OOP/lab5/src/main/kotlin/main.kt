import banks.Bank

fun main(args: Array<String>) {
    val bank = Bank()
    bank.doubtfulLimit = 50F
    bank.creditCommission = 1F
    bank.debitDailyBonusPercentage = 0.01F

    val builder = bank.getClientBuilder()
    builder.setName("Vaditel", "Ruinkin")
    builder.setAddress("Kolotuskina, Pushkina st.")
    builder.setPassportData("228")
    val vaditel = bank.createClient(builder)
    val account = bank.addClientDebitAccount(vaditel)
    account.addMoney(100F)

    builder.reset()
    builder.setName("Roberto", "from Germany")
    builder.setAddress("Korobki na Kupchino")

    val roberto = bank.createClient(builder)
    bank.addClientCreditAccount(roberto)





}