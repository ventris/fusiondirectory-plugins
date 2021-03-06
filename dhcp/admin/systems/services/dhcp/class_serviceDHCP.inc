<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2015-2016  FusionDirectory

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

class serviceDHCP extends simpleService
{
  var $objectclasses = array('dhcpServer');

  static function plInfo()
  {
    return array(
      'plShortName'   => _('DHCP service'),
      'plDescription' => _('DHCP service'),
      'plIcon'        => 'geticon.php?context=applications&icon=dhcp&size=16',
      'plForeignKeys' => array(
        'dhcpServiceDN' => 'dhcpConfiguration',
      ),

      'plProvidedAcls' => parent::generatePlProvidedAcls(static::getAttributesInfo())
    );
  }

  static function getAttributesInfo ()
  {
    return array(
      'main' => array(
        'name'  => _('DHCP configurations'),
        'class' => array('fullwidth'),
        'attrs' => array(
          new SetAttribute(
            new SelectAttribute (
              '', _('The DN of dhcpService object(s) which contain the configuration information'),
              'dhcpServiceDN'
            )
          )
        )
      ),
    );
  }

  function __construct ($dn = NULL, $parent = NULL)
  {
    $attributesInfo = $this->getAttributesInfo();
    $services = objects::ls('dhcpConfiguration');
    $attributesInfo['main']['attrs'][0]->attribute->setChoices(array_keys($services), array_values($services));
    parent::__construct($dn, $parent, $attributesInfo);
  }
}
?>
