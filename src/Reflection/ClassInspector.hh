<?hh //strict
namespace Zumb\Dein\Reflection;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\ContainerService;

class ClassInspector<Tp> extends \ReflectionClass
{
  public function is(string $name):bool
  {
    return $this->isSubclassOf($name) || $this->getName() == $name;
  }
}
