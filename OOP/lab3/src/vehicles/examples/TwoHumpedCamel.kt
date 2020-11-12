package vehicles.examples

import vehicles.GroundVehicle

class TwoHumpedCamel: GroundVehicle() {
    override val speed = 10F

    override val restInterval = 30F

    override fun restDuration(iteration: Int): Float {
        return when (iteration) {
            1 -> 5F
            else -> 8F
        }
    }
}