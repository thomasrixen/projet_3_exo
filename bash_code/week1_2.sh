if ../exe/true; then echo "true fonctionne"; fi
if ! ../exe/false; then echo "false fonctionne"; fi
if ../exe/true -a ../exe/false; then echo "Ok"; fi
if ../exe/false; 
then echo "false fonctionne"; 
else echo "False Ok";
fi