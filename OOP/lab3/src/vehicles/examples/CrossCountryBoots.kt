package vehicles.examples

import vehicles.GroundVehicle

class CrossCountryBoots: GroundVehicle() {
    override val speed = 6F

    override val restInterval = 60F

    override fun restDuration(iteration: Int): Float {
        return when (iteration) {
            1 -> 10F
            else -> 5F
        }
    }
}