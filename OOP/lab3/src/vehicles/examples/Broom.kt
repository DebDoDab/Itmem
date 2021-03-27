package vehicles.examples

import vehicles.AirVehicle

class Broom: AirVehicle() {
    override val speed = 20F

    override fun distanceReduce(distance: Float): Float {
        return distance / 1000 / 100
    }
}