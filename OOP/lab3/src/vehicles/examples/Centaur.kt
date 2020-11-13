package vehicles.examples

import vehicles.GroundVehicle

class Centaur: GroundVehicle() {
    override val speed = 15F

    override val restInterval = 8F

    override fun restDuration(iteration: Int): Float {
        return 2F
    }
}