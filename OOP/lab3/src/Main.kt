import races.GroundRace
import vehicles.examples.Broom
import vehicles.examples.Centaur
import vehicles.examples.CrossCountryBoots
import vehicles.examples.SpeedCamel

fun main(args: Array<String>) {
    val race = GroundRace(5000F)
    race.addVehicle(SpeedCamel())
    race.addVehicle(CrossCountryBoots())
    race.addVehicle(Centaur())

    val winner = race.run()
    print(winner.toString())
}
