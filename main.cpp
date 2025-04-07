// PHYS30762 Programming in C++
// Assignment 5
// Programme to model radioactive decay.
// Created by Bruno Keyworth (ID: 11021856) on 03/04/2025.

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<variant>
#include"Nucleus.h"
#include"StableNucleus.h"
#include"RadioactiveNucleus.h"
#include"Particle.h"
#include"Electron.h"
#include"Photon.h"
#include"functions.h"

int main()
{
  std::vector<std::variant<RadioactiveNucleus, StableNucleus>> nuclei;
  nuclei.reserve(4);
  nuclei.emplace_back(RadioactiveNucleus("Na-22"));
  nuclei.emplace_back(RadioactiveNucleus("Co-60"));
  nuclei.emplace_back(RadioactiveNucleus("Cs-137"));
  nuclei.emplace_back(StableNucleus("Fe-56"));

  std::cout<<"Initial nuclei data:"<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  std::cout<<"Isotope | Z   | A   | Halflife (yr) | Decayed?"<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  for(const auto& nucleus : nuclei) std::visit([](auto& n) { n.printData(); }, nucleus);
  std::cout<<std::string(80, '-')<<std::endl;
  
  std::cout<<"Emitted photon data:"<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  std::cout<<"Particle | Source | Energy"<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  std::vector<Photon> photons;
  for(auto& nucleus : nuclei)
  {
    std::visit([&photons](auto& n)
    { if constexpr (std::is_same_v<decltype(n), RadioactiveNucleus&>)
      {
        auto some_photons = n.decay();
        photons.insert(photons.end(), some_photons.begin(), some_photons.end());
      }
    }, nucleus);
  }
  std::cout<<std::string(80, '-')<<std::endl;
  
  photoelectric_effect(photons[0]);
  compton_effect(photons[1], 0.05);
  std::vector<Electron> electrons = pair_production(photons[2]);
  std::vector<Electron> more_electrons = pair_production(photons[3]);
  electrons.insert(electrons.end(), more_electrons.begin(), more_electrons.end());
  
  std::cout<<"Pair produced electrons data:"<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  std::cout<<"Particle | energy | rest mass "<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  for(Electron e : electrons) { e.printData(); }
  std::cout<<std::string(80, '-')<<std::endl;
  
  Photon photon = radiate(electrons[0]);
  
  std::cout<<"Final nuclei data:"<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  std::cout<<"Isotope | Z   | A   | Halflife (yr) | Decayed?"<<std::endl;
  std::cout<<std::string(80, '-')<<std::endl;
  for(const auto& nucleus : nuclei) std::visit([](auto& n) { n.printData(); }, nucleus);
  std::cout<<std::string(80, '-')<<std::endl;
  return 0;
}
