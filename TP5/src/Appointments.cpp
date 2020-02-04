#include "Appointments.hpp"

Appointments::Appointments(std::string filePath) : _csvHandler(CSVHandler(filePath))
{
    this->_headers = this->_csvHandler.getHeader(); // It is correct to return vector<T> as lvalue.
   // this->_appointmentsData = AppointmentsData();
    this->_appointmentsData = (this->_csvHandler.getData());
}
 std::vector<std::vector<std::string>> Appointments::filteredAppointments(unsigned int userCol, std::string userId){
            std::vector<std::vector<std::string>> filteredAppointments;
            
            std::copy_if(
        this->_appointmentsData.begin(),
        this->_appointmentsData.end(),
        std::back_inserter(filteredAppointments),
            [userId, userCol](std::vector<std::string> appointment) {
                return appointment[userCol] == userId;
            });

            return filteredAppointments;
 }

 void Appointments::fullArray(std::vector<unsigned int>& array ){
   if (array.empty())
    {
        array = std::vector<unsigned int>(this->_headers.size());
        std::iota(array.begin(), array.end(), 0);
    }

 }
   void Appointments::displayHeaderColumn(std::vector<unsigned int> headerColumn){
       
    for (unsigned int col : headerColumn)
    {
        std::cout << std::setw(this->_COLUMN_WIDTH)
                  << this->_headers[col];
    }
    std::cout << std::endl
              << std::string(headerColumn.size() * this->_COLUMN_WIDTH, '_')
              << std::endl;

}
void Appointments::printAppointments(std::vector<std::vector<std::string>> appointments,std::vector<unsigned int> column){
unsigned int appointmentIdx = 1;
for (std::vector<std::string> filteredAppointment : appointments)
    {
        std::cout << appointmentIdx++
                  << '.' 
                  << std::setw(this->_COLUMN_WIDTH - 2);

        for (unsigned int col : column)
        {
            std::cout << filteredAppointment[col].substr(0, this->_COLUMN_WIDTH - 1)
                      << std::setw(this->_COLUMN_WIDTH);
        }

        std::cout << '\n';
    }

}
void Appointments::display(unsigned int userCol, std::string userId, std::vector<unsigned int> displayedColumns)
{
    
    

    // 1. On remplit le vecteur displayedColumns par tous les indexes des colonnes du fichier CSV:
 
    fullArray(displayedColumns);
    // 2. On affiche toutes les en-têtes des colonnes voulues du fichier CSV:
    
    displayHeaderColumn(displayedColumns);
    // 3. On filtre les rendez-vous pour ne conserver ceux de l'utilisateur passé en paramètre (soit un infirmier ou un patient):

     printAppointments(filteredAppointments(userCol,userId),displayedColumns);
    // 4. On affiche ensuite les rendez-vous filtrés à l'écran:
    
}

bool Appointments::schedule(std::string patientId, std::string nurseId)
{
    std::vector<std::string> newAppointment = this->createNewAppointment(patientId, nurseId);

    for (std::vector<std::string> appointment : (this->_appointmentsData)) //plus besoin de getData
    {
        bool isOccupied = newAppointment[APPOINTMENT_DATE] == appointment[APPOINTMENT_DATE] &&
                          newAppointment[APPOINTMENT_TIME] == appointment[APPOINTMENT_TIME];
        if (isOccupied)
        {
            return false; // Schedule did not work
        }
    }
    // Update appointment list and file.
    this->_appointmentsData.push_back(newAppointment);
    this->_csvHandler.writeData(newAppointment);
    return true;
}

//     getter de nouvel attribut _appointmentsData

std::vector<std::vector<std::string>>* Appointments::getAppointmentsData(){

    return &this->_appointmentsData;
}
//   setter de nouvel attribut _appointmentsData
void Appointments::setAppointmentsData(std::vector<std::vector<std::string>> appointmentsData){
    this->_appointmentsData=appointmentsData;
}



std::vector<std::string> Appointments::createNewAppointment(std::string patientId, std::string nurseId)
{
    std::vector<std::string> newAppointment(this->_headers.size());
    newAppointment[APPOINTMENT_NURSE_ID] = nurseId;
    newAppointment[APPOINTMENT_PATIENT_ID] = patientId;

    std::cout << "\nVeuillez indiquer la date du rendez-vous [jj/mm/aaaa]: ";
    std::cin >> newAppointment[APPOINTMENT_DATE];

    std::cout << "\nVeuillez indiquer le moment du rendez-vous [AM/PM]: ";
    std::cin >> newAppointment[APPOINTMENT_TIME];

    std::cout << "\nVeuillez indiquer la raison du rendez-vous: ";
    std::cin >> newAppointment[APPOINTMENT_REASON];

    return newAppointment;
}