# bogus-project2
Overlay: XBOX Gamebar to draw the overlay externally
Kernel Driver: a shitty win32k .ptr driver which exploited and allows us to hook to read and write memory to valorant (game of choice)


Sources:

  kdmapper (modified): https://github.com/TheCruZ/kdmapper since windows does not allow you to just run any kernel driver, i used kdmapper to plant my driver into the shitty intel driver's memory
  
