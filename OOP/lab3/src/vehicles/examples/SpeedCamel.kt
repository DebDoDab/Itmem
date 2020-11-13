package vehicles.examples

import vehicles.GroundVehicle

class SpeedCamel: GroundVehicle() {
    override val speed = 40F

    override val restInterval = 10F

    override fun restDuration(iteration: Int): Float {
        return when (iteration) {
            1 -> 5F
            2 -> 6.5F
            else -> 8F
        }
    }
}