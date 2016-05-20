<?hh //strict
namespace Dein\Reflection;

use Dein\Interfaces\Provider;
use Dein\ContainerService;

class ClassInspector<Tp> extends \ReflectionClass
{
  public function is(string $name):bool
  {
    return $this->isSubclassOf($name) || $this->getName() == $name;
  }
}
