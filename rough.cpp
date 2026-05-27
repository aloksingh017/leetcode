#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class SpotSize { SMALL = 1, MEDIUM = 2, LARGE = 3 };

enum class VehicleType { MOTORCYCLE = 1, CAR = 2, BUS = 3 };

class ParkingSpot;

class Vehicle {
protected:
  std::string licensePlate;
  VehicleType vehicleType;
  int spotsNeeded;
  SpotSize preferredSpotSize;

public:
  Vehicle(const std::string &licensePlate, VehicleType vehicleType,
          int spotsNeeded, SpotSize preferredSpotSize)
      : licensePlate(licensePlate), vehicleType(vehicleType),
        spotsNeeded(spotsNeeded), preferredSpotSize(preferredSpotSize) {}

  virtual ~Vehicle() = default;

  virtual bool canFitInSpot(const ParkingSpot &spot) const = 0;

  int getSpotsNeeded() const { return spotsNeeded; }
  SpotSize getPreferredSpotSize() const { return preferredSpotSize; }
  VehicleType getType() const { return vehicleType; }
  std::string getLicensePlate() const { return licensePlate; }
};

class ParkingSpot {
private:
  int id;
  SpotSize size;
  const Vehicle *vehicle;
  bool available;

public:
  ParkingSpot(int spotId, SpotSize size)
      : id(spotId), size(size), vehicle(nullptr), available(true) {}

  bool park(const Vehicle &vehicleToPark) {
    if (!available || !vehicleToPark.canFitInSpot(*this)) {
      return false;
    }

    vehicle = &vehicleToPark;
    available = false;
    return true;
  }

  void removeVehicle() {
    vehicle = nullptr;
    available = true;
  }

  bool isAvailable() const { return available; }
  SpotSize getSize() const { return size; }
  int getId() const { return id; }
  const Vehicle *getVehicle() const { return vehicle; }
};

class Motorcycle : public Vehicle {
public:
  explicit Motorcycle(const std::string &licensePlate)
      : Vehicle(licensePlate, VehicleType::MOTORCYCLE, 1, SpotSize::SMALL) {}

  bool canFitInSpot(const ParkingSpot &spot) const override { return true; }
};

class Car : public Vehicle {
public:
  explicit Car(const std::string &licensePlate)
      : Vehicle(licensePlate, VehicleType::CAR, 1, SpotSize::MEDIUM) {}

  bool canFitInSpot(const ParkingSpot &spot) const override {
    return spot.getSize() == SpotSize::MEDIUM ||
           spot.getSize() == SpotSize::LARGE;
  }
};

class Bus : public Vehicle {
public:
  explicit Bus(const std::string &licensePlate)
      : Vehicle(licensePlate, VehicleType::BUS, 5, SpotSize::LARGE) {}

  bool canFitInSpot(const ParkingSpot &spot) const override {
    return spot.getSize() == SpotSize::LARGE;
  }
};

class Level {
private:
  int floor;
  std::vector<ParkingSpot> spots;
  int availableSpots;

  std::vector<ParkingSpot *> findAvailableSpots(const Vehicle &vehicle) {
    std::vector<ParkingSpot *> availableSpotList;

    // Bus must occupy consecutive large spots.
    if (vehicle.getType() == VehicleType::BUS) {
      std::vector<ParkingSpot *> candidate;

      for (auto &spot : spots) {
        if (spot.isAvailable() && spot.getSize() == SpotSize::LARGE) {
          candidate.push_back(&spot);

          if (static_cast<int>(candidate.size()) == vehicle.getSpotsNeeded()) {
            return candidate;
          }
        } else {
          candidate.clear();
        }
      }

      return {};
    }

    for (auto &spot : spots) {
      if (spot.isAvailable() && vehicle.canFitInSpot(spot)) {
        availableSpotList.push_back(&spot);

        if (static_cast<int>(availableSpotList.size()) >=
            vehicle.getSpotsNeeded()) {
          break;
        }
      }
    }

    return availableSpotList;
  }

public:
  Level(int floor, int numSmall, int numMedium, int numLarge)
      : floor(floor), availableSpots(numSmall + numMedium + numLarge) {
    spots.reserve(numSmall + numMedium + numLarge);
    int spotId = 0;

    for (int i = 0; i < numSmall; ++i) {
      spots.emplace_back(spotId++, SpotSize::SMALL);
    }

    for (int i = 0; i < numMedium; ++i) {
      spots.emplace_back(spotId++, SpotSize::MEDIUM);
    }

    for (int i = 0; i < numLarge; ++i) {
      spots.emplace_back(spotId++, SpotSize::LARGE);
    }
  }

  bool parkVehicle(const Vehicle &vehicle) {
    if (availableSpots < vehicle.getSpotsNeeded()) {
      return false;
    }

    std::vector<ParkingSpot *> spotList = findAvailableSpots(vehicle);

    if (static_cast<int>(spotList.size()) < vehicle.getSpotsNeeded()) {
      return false;
    }

    for (ParkingSpot *spot : spotList) {
      spot->park(vehicle);
    }

    availableSpots -= vehicle.getSpotsNeeded();
    return true;
  }

  int getFloor() const { return floor; }
  int getAvailableSpots() const { return availableSpots; }
};

class ParkingLot {
private:
  std::vector<std::unique_ptr<Level>> levels;

  ParkingLot(int numLevels, int numSpotsPerLevel) {
    for (int i = 0; i < numLevels; ++i) {
      int numSmall = static_cast<int>(numSpotsPerLevel * 0.2);
      int numMedium = static_cast<int>(numSpotsPerLevel * 0.6);
      int numLarge = numSpotsPerLevel - numSmall - numMedium;

      levels.push_back(
          std::make_unique<Level>(i, numSmall, numMedium, numLarge));
    }
  }

public:
  ParkingLot(const ParkingLot &) = delete;
  ParkingLot &operator=(const ParkingLot &) = delete;

  static ParkingLot &getInstance(int numLevels = 0, int numSpotsPerLevel = 0) {
    static ParkingLot instance(numLevels, numSpotsPerLevel);
    return instance;
  }

  bool parkVehicle(const Vehicle &vehicle) {
    for (auto &level : levels) {
      if (level->parkVehicle(vehicle)) {
        return true;
      }
    }

    return false;
  }
};

int main() {
  ParkingLot &parkingLot = ParkingLot::getInstance(3, 100);

  Car car("ABC123");
  Motorcycle motorcycle("XYZ789");
  Bus bus("BUS456");

  std::cout << std::boolalpha;

  std::cout << "Parking car: " << parkingLot.parkVehicle(car) << std::endl;

  std::cout << "Parking motorcycle: " << parkingLot.parkVehicle(motorcycle)
            << std::endl;

  std::cout << "Parking bus: " << parkingLot.parkVehicle(bus) << std::endl;

  return 0;
}