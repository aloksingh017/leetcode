#include <bits/stdc++.h>
using namespace std;
// VehicleSize enum

enum class VehicleSize { SMALL, MEDIUM, LARGE };

class Vehicle {
public:
  virtual string getLicensePlate() const = 0;
  virtual VehicleSize getSize() const = 0;
  virtual ~Vehicle() = default;
};

// Motorcycle class

class Motorcycle : public Vehicle {
private:
  string licensePlate;

public:
  Motorcycle(string licensePlate) { this->licensePlate = licensePlate; }
  string getLicensePlate() const override { return this->licensePlate; }
  VehicleSize getSize() const override { return VehicleSize::SMALL; }
};

// Car class

// Equivalent of Java Car class
class Car : public Vehicle {
private:
  string licensePlate;

public:
  Car(string licensePlate) { this->licensePlate = licensePlate; }
  string getLicensePlate() const override { return this->licensePlate; }
  VehicleSize getSize() const override { return VehicleSize::MEDIUM; }
};

// Truck class

class Truck : public Vehicle {
private:
  string licensePlate;

public:
  Truck(string licensePlate) { this->licensePlate = licensePlate; }
  string getLicensePlate() const override { return this->licensePlate; }
  VehicleSize getSize() const override { return VehicleSize::LARGE; }
};

// ParkingSpot interface

class ParkingSpot {
public:
  virtual bool isAvailable() const = 0;
  virtual void occupy(Vehicle *vehicle) = 0;
  virtual void vacate() = 0;
  virtual int getSpotNumber() const = 0;
  virtual VehicleSize getSize() const = 0;
  virtual ~ParkingSpot() = default;
};

class CompactSpot : public ParkingSpot {
private:
  int spotNumber;
  Vehicle *vehicle; // The vehicle currently occupying this spot
public:
  CompactSpot(int spotNumber) {
    this->spotNumber = spotNumber;
    this->vehicle = nullptr; // No vehicle occupying initially
  }

  int getSpotNumber() const override { return spotNumber; }

  bool isAvailable() const override { return vehicle == nullptr; }

  void occupy(Vehicle *vehicle) override {
    if (isAvailable()) {
      this->vehicle = vehicle;
    } else {
      // Spot is already occupied.
    }
  }

  void vacate() override {
    this->vehicle = nullptr; // Make the spot available
  }

  VehicleSize getSize() const override {
    return VehicleSize::SMALL; // Compact spots fit small vehicles
  }
};

// RegularSpot class

class RegularSpot : public ParkingSpot {
private:
  int spotNumber;
  Vehicle *vehicle;

public:
  RegularSpot(int spotNumber) {
    this->spotNumber = spotNumber;
    this->vehicle = nullptr;
  }

  int getSpotNumber() const override { return spotNumber; }

  bool isAvailable() const override { return vehicle == nullptr; }

  void occupy(std::shared_ptr<Vehicle> vehicle) override {
    if (isAvailable()) {
      this->vehicle = std::move(vehicle);
    } else {
      // Spot is already occupied.
    }
  }

  void vacate() override { this->vehicle = nullptr; }

  VehicleSize getSize() const override { return VehicleSize::MEDIUM; }
};

// OversizedSpot class

class OversizedSpot : public ParkingSpot {
private:
  int spotNumber;
  std::shared_ptr<Vehicle> vehicle;

public:
  explicit OversizedSpot(int spotNumber) {
    this->spotNumber = spotNumber;
    this->vehicle = nullptr;
  }

  int getSpotNumber() const override { return spotNumber; }

  bool isAvailable() const override { return vehicle == nullptr; }

  void occupy(std::shared_ptr<Vehicle> vehicle) override {
    if (isAvailable()) {
      this->vehicle = std::move(vehicle);
    } else {
      // Spot is already occupied.
    }
  }

  void vacate() override { this->vehicle = nullptr; }

  VehicleSize getSize() const override { return VehicleSize::LARGE; }
};

// ParkingManager class

class ParkingManager {
private:
  using SpotList = std::vector<std::shared_ptr<ParkingSpot>>;
  using AvailableSpotsMap =
      std::unordered_map<VehicleSize, SpotList, VehicleSizeHash>;

  AvailableSpotsMap availableSpots;
  std::unordered_map<std::shared_ptr<Vehicle>, std::shared_ptr<ParkingSpot>>
      vehicleToSpotMap;
  std::unordered_map<std::shared_ptr<ParkingSpot>, std::shared_ptr<Vehicle>>
      spotToVehicleMap;

public:
  explicit ParkingManager(AvailableSpotsMap availableSpots) {
    this->availableSpots = std::move(availableSpots);
  }

  std::shared_ptr<ParkingSpot>
  findSpotForVehicle(const std::shared_ptr<Vehicle> &vehicle) {
    VehicleSize vehicleSize = vehicle->getSize();

    for (VehicleSize size : vehicleSizeValues()) {
      if (static_cast<int>(size) >= static_cast<int>(vehicleSize)) {
        auto it = availableSpots.find(size);

        if (it == availableSpots.end()) {
          continue;
        }

        for (const auto &spot : it->second) {
          if (spot->isAvailable()) {
            return spot;
          }
        }
      }
    }

    return nullptr;
  }

  std::shared_ptr<ParkingSpot>
  parkVehicle(const std::shared_ptr<Vehicle> &vehicle) {
    std::shared_ptr<ParkingSpot> spot = findSpotForVehicle(vehicle);

    if (spot != nullptr) {
      spot->occupy(vehicle);

      vehicleToSpotMap[vehicle] = spot;
      spotToVehicleMap[spot] = vehicle;

      SpotList &spots = availableSpots[spot->getSize()];
      spots.erase(std::remove(spots.begin(), spots.end(), spot), spots.end());

      return spot;
    }

    return nullptr;
  }

  void unparkVehicle(const std::shared_ptr<Vehicle> &vehicle) {
    auto it = vehicleToSpotMap.find(vehicle);

    if (it != vehicleToSpotMap.end()) {
      std::shared_ptr<ParkingSpot> spot = it->second;

      vehicleToSpotMap.erase(it);
      spotToVehicleMap.erase(spot);

      spot->vacate();
      availableSpots[spot->getSize()].push_back(spot);
    }
  }

  std::shared_ptr<ParkingSpot>
  findVehicleBySpot(const std::shared_ptr<Vehicle> &vehicle) {
    auto it = vehicleToSpotMap.find(vehicle);

    if (it == vehicleToSpotMap.end()) {
      return nullptr;
    }

    return it->second;
  }

  std::shared_ptr<Vehicle>
  findSpotByVehicle(const std::shared_ptr<ParkingSpot> &spot) {
    auto it = spotToVehicleMap.find(spot);

    if (it == spotToVehicleMap.end()) {
      return nullptr;
    }

    return it->second;
  }
};

// Ticket class

class Ticket {
private:
  std::string ticketId;
  std::shared_ptr<Vehicle> vehicle;
  std::shared_ptr<ParkingSpot> parkingSpot;
  std::chrono::system_clock::time_point entryTime;
  std::optional<std::chrono::system_clock::time_point> exitTime;

public:
  Ticket(std::string ticketId, std::shared_ptr<Vehicle> vehicle,
         std::shared_ptr<ParkingSpot> parkingSpot,
         std::chrono::system_clock::time_point entryTime) {
    this->ticketId = std::move(ticketId);
    this->vehicle = std::move(vehicle);
    this->parkingSpot = std::move(parkingSpot);
    this->entryTime = entryTime;
    this->exitTime = std::nullopt;
  }

  long double calculateParkingDuration() const {
    auto endTime = exitTime.value_or(std::chrono::system_clock::now());

    auto minutes =
        std::chrono::duration_cast<std::chrono::minutes>(endTime - entryTime)
            .count();

    return static_cast<long double>(minutes);
  }

  std::string getTicketId() const { return ticketId; }

  std::shared_ptr<Vehicle> getVehicle() const { return vehicle; }

  std::shared_ptr<ParkingSpot> getParkingSpot() const { return parkingSpot; }

  std::chrono::system_clock::time_point getEntryTime() const {
    return entryTime;
  }

  std::optional<std::chrono::system_clock::time_point> getExitTime() const {
    return exitTime;
  }

  void setExitTime(std::chrono::system_clock::time_point exitTime) {
    this->exitTime = exitTime;
  }
};

// FareStrategy interface

class FareStrategy {
public:
  virtual long double calculateFare(const Ticket &ticket,
                                    long double inputFare) const = 0;

  virtual ~FareStrategy() = default;
};

// BaseFareStrategy class

class BaseFareStrategy : public FareStrategy {
private:
  static constexpr long double SMALL_VEHICLE_RATE = 1.0L;
  static constexpr long double MEDIUM_VEHICLE_RATE = 2.0L;
  static constexpr long double LARGE_VEHICLE_RATE = 3.0L;

public:
  long double calculateFare(const Ticket &ticket,
                            long double inputFare) const override {
    long double fare = inputFare;
    long double rate;

    switch (ticket.getVehicle()->getSize()) {
    case VehicleSize::MEDIUM:
      rate = MEDIUM_VEHICLE_RATE;
      break;

    case VehicleSize::LARGE:
      rate = LARGE_VEHICLE_RATE;
      break;

    default:
      rate = SMALL_VEHICLE_RATE;
      break;
    }

    fare = fare + rate * ticket.calculateParkingDuration();

    return fare;
  }
};

// PeakHoursFareStrategy class

class PeakHoursFareStrategy : public FareStrategy {
private:
  static constexpr long double PEAK_HOURS_MULTIPLIER = 1.5L;

  bool isPeakHours(std::chrono::system_clock::time_point time) const {
    std::time_t timeValue = std::chrono::system_clock::to_time_t(time);
    std::tm localTime{};

#if defined(_WIN32)
    localtime_s(&localTime, &timeValue);
#else
    localtime_r(&timeValue, &localTime);
#endif

    int hour = localTime.tm_hour;

    return (hour >= 7 && hour <= 10) || (hour >= 16 && hour <= 19);
  }

public:
  PeakHoursFareStrategy() = default;

  long double calculateFare(const Ticket &ticket,
                            long double inputFare) const override {
    long double fare = inputFare;

    if (isPeakHours(ticket.getEntryTime())) {
      fare = fare * PEAK_HOURS_MULTIPLIER;
    }

    return fare;
  }
};

// FareCalculator class

class FareCalculator {
private:
  std::vector<std::shared_ptr<FareStrategy>> fareStrategies;

public:
  explicit FareCalculator(
      std::vector<std::shared_ptr<FareStrategy>> fareStrategies) {
    this->fareStrategies = std::move(fareStrategies);
  }

  long double calculateFare(const Ticket &ticket) const {
    long double fare = 0.0L;

    for (const auto &strategy : fareStrategies) {
      fare = strategy->calculateFare(ticket, fare);
    }

    return fare;
  }
};

// ParkingLot class

class ParkingLot {
private:
  std::shared_ptr<ParkingManager> parkingManager;
  FareCalculator fareCalculator;
  int ticketSequence;

  std::string generateTicketId() {
    ++ticketSequence;
    return "TICKET-" + std::to_string(ticketSequence);
  }

public:
  ParkingLot(std::shared_ptr<ParkingManager> parkingManager,
             FareCalculator fareCalculator)
      : fareCalculator(std::move(fareCalculator)) {
    this->parkingManager = std::move(parkingManager);
    this->ticketSequence = 0;
  }

  std::shared_ptr<Ticket>
  enterVehicle(const std::shared_ptr<Vehicle> &vehicle) {
    std::shared_ptr<ParkingSpot> spot = parkingManager->parkVehicle(vehicle);

    if (spot != nullptr) {
      std::shared_ptr<Ticket> ticket = std::make_shared<Ticket>(
          generateTicketId(), vehicle, spot, std::chrono::system_clock::now());

      return ticket;
    } else {
      return nullptr;
    }
  }

  void leaveVehicle(const std::shared_ptr<Ticket> &ticket) {
    if (ticket != nullptr && !ticket->getExitTime().has_value()) {
      ticket->setExitTime(std::chrono::system_clock::now());

      parkingManager->unparkVehicle(ticket->getVehicle());

      long double fare = fareCalculator.calculateFare(*ticket);
      (void)fare;
    } else {
      // Invalid ticket or vehicle already exited.
    }
  }
};