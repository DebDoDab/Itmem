package races

import vehicles.Vehicle

abstract class Race<T> where T: Vehicle {
    protected abstract val distance: Float
    private val vehicles = mutableListOf<T>()

    fun addVehicle(vehicle: T) {
        vehicles.add(vehicle)
    }

    fun addVehicles(vehicles: List<T>) {
        vehicles.forEach { this.addVehicle(it) }
    }

    fun run(): T? {
        if (vehicles.isEmpty()) {
            return null
        }
        var fastestVehicle: T? = null
        var fastestTime: Float? = null

        for (vehicle in vehicles) {
            val raceTime = vehicle.run(distance)
            if (fastestTime == null || fastestTime > raceTime) {
                fastestVehicle = vehicle
                fastestTime = raceTime
            }
        }
        return fastestVehicle
    }
}
