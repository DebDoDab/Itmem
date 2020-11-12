package vehicles.examples

import vehicles.AirVehicle

class MagicCarpet: AirVehicle() {
    override val speed = 10F

    override fun distanceReduce(distance: Float): Float {
        return when {
            distance < 1000F -> 0F
            distance < 5000F -> 0.03F
            distance < 10000F -> 0.1F
            else -> 0.05F
        }
    }
}