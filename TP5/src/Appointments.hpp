#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

#include "Constants.hpp"
#include "CSVHandler.hpp"
//#include "AppointmentsData.hpp" // devenu inutil

class Appointments
{
public:
    Appointments(std::string filePath);

    // la méthode deplacée depuis la AppointmentsData
    std::vector<std::vector<std::string>>* getAppointmentsData();
    void setAppointmentsData(std::vector<std::vector<std::string>> appointmentsData);

   //On crée cette méthode qui va renvoyer une liste filtrée des rendez-vous d’un patient qu’elle prend en paramètre 
    std::vector<std::vector<std::string>> filteredAppointments(unsigned int userCol, std::string userId);

   // Cette méthode va permettre d’afficher la colonne d’entête
    void displayHeaderColumn(std::vector<unsigned int> headerColumn={});

  // Cette méthode permet de remplir le tableau displedColumn
   void fullArray(std::vector<unsigned int>& array );

    //Une méthode va affiche une liste de RDV qu’elle prend en paramètre
    void printAppointments(std::vector<std::vector<std::string>> appointments,std::vector<unsigned int> column={});

    void display(unsigned int userCol, std::string userId, std::vector<unsigned int> displayedColumns = {});
    bool schedule(std::string patientId, std::string nurseId);

private:
    std::vector<std::string> createNewAppointment(std::string patientId, std::string nurseId);
   //l'attribut est remplacé
    std::vector<std::vector<std::string>> _appointmentsData;
    std::vector<std::string> _headers;
    CSVHandler _csvHandler;

    const unsigned int _COLUMN_WIDTH = 14;
};
