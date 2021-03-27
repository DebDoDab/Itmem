package vehicles.examples

import vehicles.AirVehicle

class Mortar: AirVehicle() {
    override val speed = 8F

    override fun distanceReduce(distance: Float): Float {
        return 0.06F
    }
}