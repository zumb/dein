<?hh //strict
namespace Zumb\Dein;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;

class ProvidersPool
{
  protected  Map<classname<mixed>, Provider<mixed>> $providers = Map{};

  public function __construct(
    protected Instantiator $instantiator
  ) {}

  public function add(Provider<mixed> $provider, ?classname<mixed> $classTarget = null):this
  {
    if($classTarget === null) {
      $getMethod = $this->instantiator->method($provider, "get");
      $classTarget = $getMethod->getReturnTypeText();
    }
    $this->providers->set($classTarget, $provider);
    return $this;
  }

  public function get(ClassInspector<mixed> $class):?Provider<mixed>
  {
    foreach($this->providers as $returns => $provider) {
      if($class->is($returns)) {
        return $provider;
      }
    }
    return null;
  }
}
