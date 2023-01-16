import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { JwtService } from 'src/app/srv/jwt.service';

@Component({
  selector: 'app-navbar',
  template: `
    <button (click)="navToHome()">Home</button>
    
    <button (click)="navToProfile()" *ngIf="loggedIn()">Profile</button>
    <button (click)="logout()" *ngIf="loggedIn()">Logout</button>

    <button (click)="navToLogin()" *ngIf="loggedOut()">Login</button>
    <button (click)="navToRegister()" *ngIf="loggedOut()">Register</button>
  `
})
export class NavbarComponent {

  constructor(
    private router: Router,
    private jwtService: JwtService
  ) {}

  loggedOut(): boolean { return this.jwtService.isJwtExpired() }
  loggedIn(): boolean { return !this.jwtService.isJwtExpired() }

  navToHome() { this.router.navigate(['']) }
  navToLogin() { this.router.navigate(['login']) }
  navToRegister() { this.router.navigate(['register']) }
  navToProfile() { this.router.navigate(['profile']) }

  logout() {
    this.jwtService.deleteJwt()
    this.router.navigate([''])
  }

}
