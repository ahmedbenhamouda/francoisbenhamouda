// Generated by dia2code
#ifndef STATE__PORTEMONNAIE__H
#define STATE__PORTEMONNAIE__H


namespace state {

  /// class PorteMonnaie - 
  class PorteMonnaie {
    // Attributes
  public:
    int argent     = 15000;
    // Operations
  public:
    PorteMonnaie ();
    int getArgent ();
    void achat (int argent);
    void gainTour (int argent);
    ~PorteMonnaie ();
    // Setters and Getters
  };

};

#endif
