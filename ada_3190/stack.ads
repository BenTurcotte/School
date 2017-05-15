------------------------------------------
--       name:  Ben Turcotte            --
--         ID:  Bturcott                --
--          #:  0832217                 --
--      email:  bturcott@mail.guelph.ca --
-- assignment:  2                       --
--      class:  CIS*3190                --
------------------------------------------
-- Simple stack package.
-- Elements in the stack are Coordinate types
-- Intended use: a2.adb uses this package

package stack is

  type Coordinate is record
    x : Integer;
    y : Integer;
  end record;
  type Stack_of_coordinates is Array(1..5000) of Coordinate;

  procedure clear(usr_stack : in out Stack_of_coordinates);
  function  size(usr_stack : in Stack_of_coordinates) return Integer;
  procedure push (usr_stack : in out Stack_of_coordinates; new_coord : in Coordinate);
  function  top  (usr_stack : in Stack_of_coordinates) return Coordinate;
  procedure pop  (usr_stack : in out Stack_of_coordinates; popped : in out Coordinate);

end stack;