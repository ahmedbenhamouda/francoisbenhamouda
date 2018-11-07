// Generated by dia2code
#ifndef STATE__POSITION__H
#define STATE__POSITION__H


namespace state {

  /// class Position - 
  class Position {
    // Attributes
  private:
    int x;
    int y;
    // Operations
  public:
    Position ();
    Position (int x, int y);
    int getX () const;
    int getY () const;
    bool operator== (Position const& pos);
    ~Position ();
    // Setters and Getters
  };

};

#endif
