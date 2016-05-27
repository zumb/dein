<?php

namespace spec\Zumb\Dein;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Dein\Instantiator;
use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;
use Zumb\Dein\Providers\SingletonProvider;

class stdClassProvider extends SingletonProvider<\stdClass> {}

class ProvidersPoolSpec extends ObjectBehavior
{
  public function let($instantiator, $method, $provider, $inspector, $resolver, $providers)
  {
    $inspector->beADoubleOf(ClassInspector::class);
    $provider->beADoubleOf(Provider::class);
    $method->beADoubleOf(\ReflectionMethod::class);
    $instantiator->beADoubleOf(Instantiator::class);
    $this->beConstructedWith($instantiator);
  }

  public function it_adds_a_provider_instance($provider, $instantiator, $method, $inspector)
  {
    $method->getReturnTypeText()
      ->willReturn("SomeClass");
    $instantiator->method($provider, "get")
      ->willReturn($method);
    $inspector->is("SomeClass")
      ->willReturn(true);
    $this->add($provider);
    $this->get($inspector)
      ->shouldReturn($provider);
  }

  public function it_overwrites_class_target($instantiator, $inspector)
  {
    $provider = new stdClassProvider(new \stdClass());
    $instantiator->method($provider, "get")
      ->willReturn(new \Reflectionmethod($provider, "get"));
    $inspector->is("stdClass")
      ->willReturn(true);
    $this->add($provider, \stdClass::class);
    $this->get($inspector)
      ->shouldReturn($provider);
  }
}
